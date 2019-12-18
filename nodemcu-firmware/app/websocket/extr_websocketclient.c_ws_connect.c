#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int connectionState; int isSecure; int port; struct espconn* conn; scalar_t__ unhealthyPoints; scalar_t__ payloadOriginalOpCode; scalar_t__ payloadBufferLen; int /*<<< orphan*/ * payloadBuffer; scalar_t__ frameBufferLen; int /*<<< orphan*/ * frameBuffer; scalar_t__ knownFailureCode; int /*<<< orphan*/ * expectedSecKey; void* path; void* hostname; int /*<<< orphan*/  (* onFailure ) (TYPE_2__*,int) ;} ;
typedef  TYPE_2__ ws_info ;
struct TYPE_9__ {TYPE_3__* tcp; } ;
struct espconn {TYPE_2__* reverse; TYPE_1__ proto; int /*<<< orphan*/  state; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  int /*<<< orphan*/  hostname ;
struct TYPE_11__ {int remote_port; int /*<<< orphan*/  local_port; } ;
typedef  TYPE_3__ esp_tcp ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ESPCONN_INPROGRESS ; 
 int /*<<< orphan*/  ESPCONN_NONE ; 
 int /*<<< orphan*/  ESPCONN_TCP ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int PORT_INSECURE ; 
 int PORT_MAX_VALUE ; 
 int PORT_SECURE ; 
 char* PROTOCOL_INSECURE ; 
 char* PROTOCOL_SECURE ; 
 int atoi (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dns_callback (char*,int /*<<< orphan*/ *,struct espconn*) ; 
 scalar_t__ espconn_gethostbyname (struct espconn*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*,int /*<<< orphan*/ *,struct espconn*)) ; 
 int /*<<< orphan*/  espconn_port () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 char* strchr (char const*,char) ; 
 void* strdup (char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int) ; 

void ws_connect(ws_info *ws, const char *url) {
  NODE_DBG("ws_connect called\n");

  if (ws == NULL) {
    NODE_DBG("ws_connect ws_info argument is null!");
    return;
  }

  if (url == NULL) {
    NODE_DBG("url is null!");
    return;
  }

  // Extract protocol - either ws or wss
  bool isSecure = strncasecmp(url, PROTOCOL_SECURE, strlen(PROTOCOL_SECURE)) == 0;

  if (isSecure) {
    url += strlen(PROTOCOL_SECURE);
  } else {
    if (strncasecmp(url, PROTOCOL_INSECURE, strlen(PROTOCOL_INSECURE)) != 0) {
      NODE_DBG("Failed to extract protocol from: %s\n", url);
      if (ws->onFailure) ws->onFailure(ws, -1);
      return;
    }
    url += strlen(PROTOCOL_INSECURE);
  }

  // Extract path - it should start with '/'
  char *path = strchr(url, '/');

  // Extract hostname, possibly including port
  char hostname[256];
  if (path) {
    if (path - url >= sizeof(hostname)) {
      NODE_DBG("Hostname too large");
      if (ws->onFailure) ws->onFailure(ws, -2);
      return;
    }
    memcpy(hostname, url, path - url);
    hostname[path - url] = '\0';
  } else {
    // no path found, assuming the url only refers to the hostname and possibly the port
    memcpy(hostname, url, strlen(url));
    hostname[strlen(url)] = '\0';
    path = "/";
  }

  // Extract port from hostname, if available
  char *portInHostname = strchr(hostname, ':');
  int port;
  if (portInHostname) {
    port = atoi(portInHostname + 1);
    if (port <= 0 || port > PORT_MAX_VALUE) {
      NODE_DBG("Invalid port number\n");
      if (ws->onFailure) ws->onFailure(ws, -3);
      return;
    }
    hostname[strlen(hostname) - strlen(portInHostname)] = '\0'; // remove port from hostname
  } else {
    port = isSecure ? PORT_SECURE : PORT_INSECURE;
  }

  if (strlen(hostname) == 0) {
    NODE_DBG("Failed to extract hostname\n");
    if (ws->onFailure) ws->onFailure(ws, -4);
    return;
  }

  NODE_DBG("secure protocol = %d\n", isSecure);
  NODE_DBG("hostname = %s\n", hostname);
  NODE_DBG("port = %d\n", port);
  NODE_DBG("path = %s\n", path);

  // Prepare internal ws_info
  ws->connectionState = 1;
  ws->isSecure = isSecure;
  ws->hostname = strdup(hostname);
  ws->port = port;
  ws->path = strdup(path);
  ws->expectedSecKey = NULL;
  ws->knownFailureCode = 0;
  ws->frameBuffer = NULL;
  ws->frameBufferLen = 0;
  ws->payloadBuffer = NULL;
  ws->payloadBufferLen = 0;
  ws->payloadOriginalOpCode = 0;
  ws->unhealthyPoints = 0;

  // Prepare espconn
  struct espconn *conn = (struct espconn *) calloc(1,sizeof(struct espconn));
  conn->type = ESPCONN_TCP;
  conn->state = ESPCONN_NONE;
  conn->proto.tcp = (esp_tcp *) calloc(1,sizeof(esp_tcp));
  conn->proto.tcp->local_port = espconn_port();
  conn->proto.tcp->remote_port = ws->port;

  conn->reverse = ws;
  ws->conn = conn;

  // Attempt to resolve hostname address
  ip_addr_t  addr;
  err_t result = espconn_gethostbyname(conn, hostname, &addr, dns_callback);

  if (result == ESPCONN_INPROGRESS) {
    NODE_DBG("DNS pending\n");
  } else {
    dns_callback(hostname, &addr, conn);
  }

  return;
}