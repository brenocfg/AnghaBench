#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* frameBuffer; unsigned short frameBufferLen; int knownFailureCode; char* payloadBuffer; int payloadOriginalOpCode; int payloadBufferLen; int connectionState; scalar_t__ isSecure; int /*<<< orphan*/  (* onReceive ) (TYPE_1__*,int,char*,int) ;int /*<<< orphan*/  timeoutTimer; scalar_t__ unhealthyPoints; } ;
typedef  TYPE_1__ ws_info ;
typedef  int uint64_t ;
struct espconn {scalar_t__ reverse; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int WS_OPCODE_CLOSE ; 
 int WS_OPCODE_CONTINUATION ; 
 int WS_OPCODE_PING ; 
 int WS_OPCODE_PONG ; 
 int /*<<< orphan*/  WS_PING_INTERVAL_MS ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  espconn_disconnect (struct espconn*) ; 
 int /*<<< orphan*/  espconn_regist_sentcb (struct espconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  espconn_secure_disconnect (struct espconn*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned short) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 void* realloc (char*,unsigned short) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,char*,int) ; 
 int /*<<< orphan*/  ws_closeSentCallback ; 
 int /*<<< orphan*/  ws_sendFrame (struct espconn*,int,char const*,unsigned short) ; 

__attribute__((used)) static void ws_receiveCallback(void *arg, char *buf, unsigned short len) {
  NODE_DBG("ws_receiveCallback %d \n", len);
  struct espconn *conn = (struct espconn *) arg;
  ws_info *ws = (ws_info *) conn->reverse;

  ws->unhealthyPoints = 0; // received data, connection is healthy
  os_timer_disarm(&ws->timeoutTimer); // reset ping check
  os_timer_arm(&ws->timeoutTimer, WS_PING_INTERVAL_MS, true);


  char *b = buf;
  if (ws->frameBuffer != NULL) { // Append previous frameBuffer with new content
    NODE_DBG("Appending new frameBuffer to old one \n");

    ws->frameBuffer = realloc(ws->frameBuffer, ws->frameBufferLen + len);
    if (ws->frameBuffer == NULL) {
      NODE_DBG("Failed to allocate new framebuffer, disconnecting...\n");

      ws->knownFailureCode = -8;
      if (ws->isSecure)
        espconn_secure_disconnect(conn);
      else
        espconn_disconnect(conn);
      return;
    }
    memcpy(ws->frameBuffer + ws->frameBufferLen, b, len);

    ws->frameBufferLen += len;

    len = ws->frameBufferLen;
    b = ws->frameBuffer;
    NODE_DBG("New frameBufferLen: %d\n", len);
  }

  while (b != NULL) { // several frames can be present, b pointer will be moved to the next frame
    NODE_DBG("b[0] = %d \n", b[0]);
    NODE_DBG("b[1] = %d \n", b[1]);
    NODE_DBG("b[2] = %d \n", b[2]);
    NODE_DBG("b[3] = %d \n", b[3]);
    NODE_DBG("b[4] = %d \n", b[4]);
    NODE_DBG("b[5] = %d \n", b[5]);
    NODE_DBG("b[6] = %d \n", b[6]);
    NODE_DBG("b[7] = %d \n", b[7]);

    int isFin = b[0] & 0x80 ? 1 : 0;
    int opCode = b[0] & 0x0f;
    int hasMask = b[1] & 0x80 ? 1 : 0;
    uint64_t payloadLength = b[1] & 0x7f;
    int bufOffset = 2;
    if (payloadLength == 126) {
      payloadLength = (b[2] << 8) + b[3];
      bufOffset = 4;
    } else if (payloadLength == 127) { // this will clearly not hold in heap, abort??
      payloadLength = (b[2] << 24) + (b[3] << 16) + (b[4] << 8) + b[5];
      bufOffset = 6;
    }

    if (hasMask) {
      int maskOffset = bufOffset;
      bufOffset += 4;

      int i;
      for (i = 0; i < payloadLength; i++) {
        b[bufOffset + i] ^= b[maskOffset + i % 4]; // apply mask to decode payload
      }
    }

    if (payloadLength > len - bufOffset) {
      NODE_DBG("INCOMPLETE Frame \n");
      if (ws->frameBuffer == NULL) {
        NODE_DBG("Allocing new frameBuffer \n");
        ws->frameBuffer = calloc(1,len);
        if (ws->frameBuffer == NULL) {
          NODE_DBG("Failed to allocate framebuffer, disconnecting... \n");

          ws->knownFailureCode = -9;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }
        memcpy(ws->frameBuffer, b, len);
        ws->frameBufferLen = len;
      }
      break; // since the buffer were already concat'ed, wait for the next receive
    }

    if (!isFin) {
      NODE_DBG("PARTIAL frame! Should concat payload and later restore opcode\n");
      if(ws->payloadBuffer == NULL) {
        NODE_DBG("Allocing new payloadBuffer \n");
        ws->payloadBuffer = calloc(1,payloadLength);
        if (ws->payloadBuffer == NULL) {
          NODE_DBG("Failed to allocate payloadBuffer, disconnecting...\n");

          ws->knownFailureCode = -10;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }
        memcpy(ws->payloadBuffer, b + bufOffset, payloadLength);
        ws->frameBufferLen = payloadLength;
        ws->payloadOriginalOpCode = opCode;
      } else {
        NODE_DBG("Appending new payloadBuffer to old one \n");
        ws->payloadBuffer = realloc(ws->payloadBuffer, ws->payloadBufferLen + payloadLength);
        if (ws->payloadBuffer == NULL) {
          NODE_DBG("Failed to allocate new framebuffer, disconnecting...\n");

          ws->knownFailureCode = -11;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }
        memcpy(ws->payloadBuffer + ws->payloadBufferLen, b + bufOffset, payloadLength);

        ws->payloadBufferLen += payloadLength;
      }
    } else {
      char *payload;
      if (opCode == WS_OPCODE_CONTINUATION) {
        NODE_DBG("restoring original opcode\n");
        if (ws->payloadBuffer == NULL) {
          NODE_DBG("Got FIN continuation frame but didn't receive any beforehand, disconnecting...\n");

          ws->knownFailureCode = -15;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }
        // concat buffer with payload
        payload = calloc(1,ws->payloadBufferLen + payloadLength);

        if (payload == NULL) {
          NODE_DBG("Failed to allocate new framebuffer, disconnecting...\n");

          ws->knownFailureCode = -12;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }
        memcpy(payload, ws->payloadBuffer, ws->payloadBufferLen);
        memcpy(payload + ws->payloadBufferLen, b + bufOffset, payloadLength);

        os_free(ws->payloadBuffer); // free previous buffer
        ws->payloadBuffer = NULL;

        payloadLength += ws->payloadBufferLen;
        ws->payloadBufferLen = 0;

        opCode = ws->payloadOriginalOpCode;
        ws->payloadOriginalOpCode = 0;
      } else {
        int extensionDataOffset = 0;

        if (opCode == WS_OPCODE_CLOSE && payloadLength > 0) {
          unsigned int reasonCode = b[bufOffset] << 8 + b[bufOffset + 1];
          NODE_DBG("Closing due to: %d\n", reasonCode); // Must not be shown to client as per spec
          extensionDataOffset += 2;
        }

        payload = calloc(1,payloadLength - extensionDataOffset + 1);
        if (payload == NULL) {
          NODE_DBG("Failed to allocate payload, disconnecting...\n");

          ws->knownFailureCode = -13;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }

        memcpy(payload, b + bufOffset + extensionDataOffset, payloadLength - extensionDataOffset);
        payload[payloadLength - extensionDataOffset] = '\0';
      }

      NODE_DBG("isFin %d \n", isFin);
      NODE_DBG("opCode %d \n", opCode);
      NODE_DBG("hasMask %d \n", hasMask);
      NODE_DBG("payloadLength %d \n", payloadLength);
      NODE_DBG("len %d \n", len);
      NODE_DBG("bufOffset %d \n", bufOffset);

      if (opCode == WS_OPCODE_CLOSE) {
        NODE_DBG("Closing message: %s\n", payload); // Must not be shown to client as per spec

        espconn_regist_sentcb(conn, ws_closeSentCallback);
        ws_sendFrame(conn, WS_OPCODE_CLOSE, (const char *) (b + bufOffset), (unsigned short) payloadLength);
        ws->connectionState = 4;
      } else if (opCode == WS_OPCODE_PING) {
        ws_sendFrame(conn, WS_OPCODE_PONG, (const char *) (b + bufOffset), (unsigned short) payloadLength);
      } else if (opCode == WS_OPCODE_PONG) {
        // ping alarm was already reset...
      } else {
        if (ws->onReceive) ws->onReceive(ws, payloadLength, payload, opCode);
      }
      os_free(payload);
    }

    bufOffset += payloadLength;
    NODE_DBG("bufOffset %d \n", bufOffset);
    if (bufOffset == len) { // (bufOffset > len) won't happen here because it's being checked earlier
      b = NULL;
      if (ws->frameBuffer != NULL) { // the last frame inside buffer was processed
        os_free(ws->frameBuffer);
        ws->frameBuffer = NULL;
        ws->frameBufferLen = 0;
      }
    } else {
      len -= bufOffset;
      b += bufOffset; // move b to next frame
      if (ws->frameBuffer != NULL) {
        NODE_DBG("Reallocing frameBuffer to remove consumed frame\n");

        ws->frameBuffer = realloc(ws->frameBuffer, ws->frameBufferLen + len);
        if (ws->frameBuffer == NULL) {
          NODE_DBG("Failed to allocate new frame buffer, disconnecting...\n");

          ws->knownFailureCode = -14;
          if (ws->isSecure)
            espconn_secure_disconnect(conn);
          else
            espconn_disconnect(conn);
          return;
        }
        memcpy(ws->frameBuffer + ws->frameBufferLen, b, len);

        ws->frameBufferLen += len;
        b = ws->frameBuffer;
      }
    }
  }
}