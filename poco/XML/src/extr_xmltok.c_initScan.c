#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** encPtr; } ;
typedef  TYPE_1__ INIT_ENCODING ;
typedef  int /*<<< orphan*/  ENCODING ;

/* Variables and functions */
 size_t INIT_ENC_INDEX (TYPE_1__ const*) ; 
 int ISO_8859_1_ENC ; 
#define  UTF_16BE_ENC 130 
#define  UTF_16LE_ENC 129 
#define  UTF_16_ENC 128 
 size_t UTF_8_ENC ; 
 int XML_CONTENT_STATE ; 
 int XML_TOK_BOM ; 
 int XML_TOK_NONE ; 
 int XML_TOK_PARTIAL ; 
 int XmlTok (int /*<<< orphan*/  const*,int,char const*,char const*,char const**) ; 

__attribute__((used)) static int
initScan(const ENCODING *const *encodingTable, const INIT_ENCODING *enc,
         int state, const char *ptr, const char *end, const char **nextTokPtr) {
  const ENCODING **encPtr;

  if (ptr >= end)
    return XML_TOK_NONE;
  encPtr = enc->encPtr;
  if (ptr + 1 == end) {
    /* only a single byte available for auto-detection */
#ifndef XML_DTD /* FIXME */
    /* a well-formed document entity must have more than one byte */
    if (state != XML_CONTENT_STATE)
      return XML_TOK_PARTIAL;
#endif
    /* so we're parsing an external text entity... */
    /* if UTF-16 was externally specified, then we need at least 2 bytes */
    switch (INIT_ENC_INDEX(enc)) {
    case UTF_16_ENC:
    case UTF_16LE_ENC:
    case UTF_16BE_ENC:
      return XML_TOK_PARTIAL;
    }
    switch ((unsigned char)*ptr) {
    case 0xFE:
    case 0xFF:
    case 0xEF: /* possibly first byte of UTF-8 BOM */
      if (INIT_ENC_INDEX(enc) == ISO_8859_1_ENC && state == XML_CONTENT_STATE)
        break;
      /* fall through */
    case 0x00:
    case 0x3C:
      return XML_TOK_PARTIAL;
    }
  } else {
    switch (((unsigned char)ptr[0] << 8) | (unsigned char)ptr[1]) {
    case 0xFEFF:
      if (INIT_ENC_INDEX(enc) == ISO_8859_1_ENC && state == XML_CONTENT_STATE)
        break;
      *nextTokPtr = ptr + 2;
      *encPtr = encodingTable[UTF_16BE_ENC];
      return XML_TOK_BOM;
    /* 00 3C is handled in the default case */
    case 0x3C00:
      if ((INIT_ENC_INDEX(enc) == UTF_16BE_ENC
           || INIT_ENC_INDEX(enc) == UTF_16_ENC)
          && state == XML_CONTENT_STATE)
        break;
      *encPtr = encodingTable[UTF_16LE_ENC];
      return XmlTok(*encPtr, state, ptr, end, nextTokPtr);
    case 0xFFFE:
      if (INIT_ENC_INDEX(enc) == ISO_8859_1_ENC && state == XML_CONTENT_STATE)
        break;
      *nextTokPtr = ptr + 2;
      *encPtr = encodingTable[UTF_16LE_ENC];
      return XML_TOK_BOM;
    case 0xEFBB:
      /* Maybe a UTF-8 BOM (EF BB BF) */
      /* If there's an explicitly specified (external) encoding
         of ISO-8859-1 or some flavour of UTF-16
         and this is an external text entity,
         don't look for the BOM,
         because it might be a legal data.
      */
      if (state == XML_CONTENT_STATE) {
        int e = INIT_ENC_INDEX(enc);
        if (e == ISO_8859_1_ENC || e == UTF_16BE_ENC || e == UTF_16LE_ENC
            || e == UTF_16_ENC)
          break;
      }
      if (ptr + 2 == end)
        return XML_TOK_PARTIAL;
      if ((unsigned char)ptr[2] == 0xBF) {
        *nextTokPtr = ptr + 3;
        *encPtr = encodingTable[UTF_8_ENC];
        return XML_TOK_BOM;
      }
      break;
    default:
      if (ptr[0] == '\0') {
        /* 0 isn't a legal data character. Furthermore a document
           entity can only start with ASCII characters.  So the only
           way this can fail to be big-endian UTF-16 if it it's an
           external parsed general entity that's labelled as
           UTF-16LE.
        */
        if (state == XML_CONTENT_STATE && INIT_ENC_INDEX(enc) == UTF_16LE_ENC)
          break;
        *encPtr = encodingTable[UTF_16BE_ENC];
        return XmlTok(*encPtr, state, ptr, end, nextTokPtr);
      } else if (ptr[1] == '\0') {
        /* We could recover here in the case:
            - parsing an external entity
            - second byte is 0
            - no externally specified encoding
            - no encoding declaration
           by assuming UTF-16LE.  But we don't, because this would mean when
           presented just with a single byte, we couldn't reliably determine
           whether we needed further bytes.
        */
        if (state == XML_CONTENT_STATE)
          break;
        *encPtr = encodingTable[UTF_16LE_ENC];
        return XmlTok(*encPtr, state, ptr, end, nextTokPtr);
      }
      break;
    }
  }
  *encPtr = encodingTable[INIT_ENC_INDEX(enc)];
  return XmlTok(*encPtr, state, ptr, end, nextTokPtr);
}