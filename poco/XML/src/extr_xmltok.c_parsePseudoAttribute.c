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
struct TYPE_4__ {int minBytesPerChar; } ;
typedef  TYPE_1__ ENCODING ;

/* Variables and functions */
 int ASCII_0 ; 
 int ASCII_9 ; 
 int ASCII_A ; 
 int ASCII_APOS ; 
 int ASCII_EQUALS ; 
 int ASCII_MINUS ; 
 int ASCII_PERIOD ; 
 int ASCII_QUOT ; 
 int ASCII_UNDERSCORE ; 
 int ASCII_Z ; 
 int ASCII_a ; 
 int ASCII_z ; 
 scalar_t__ isSpace (int) ; 
 int toAscii (TYPE_1__ const*,char const*,char const*) ; 

__attribute__((used)) static int
parsePseudoAttribute(const ENCODING *enc, const char *ptr, const char *end,
                     const char **namePtr, const char **nameEndPtr,
                     const char **valPtr, const char **nextTokPtr) {
  int c;
  char open;
  if (ptr == end) {
    *namePtr = NULL;
    return 1;
  }
  if (! isSpace(toAscii(enc, ptr, end))) {
    *nextTokPtr = ptr;
    return 0;
  }
  do {
    ptr += enc->minBytesPerChar;
  } while (isSpace(toAscii(enc, ptr, end)));
  if (ptr == end) {
    *namePtr = NULL;
    return 1;
  }
  *namePtr = ptr;
  for (;;) {
    c = toAscii(enc, ptr, end);
    if (c == -1) {
      *nextTokPtr = ptr;
      return 0;
    }
    if (c == ASCII_EQUALS) {
      *nameEndPtr = ptr;
      break;
    }
    if (isSpace(c)) {
      *nameEndPtr = ptr;
      do {
        ptr += enc->minBytesPerChar;
      } while (isSpace(c = toAscii(enc, ptr, end)));
      if (c != ASCII_EQUALS) {
        *nextTokPtr = ptr;
        return 0;
      }
      break;
    }
    ptr += enc->minBytesPerChar;
  }
  if (ptr == *namePtr) {
    *nextTokPtr = ptr;
    return 0;
  }
  ptr += enc->minBytesPerChar;
  c = toAscii(enc, ptr, end);
  while (isSpace(c)) {
    ptr += enc->minBytesPerChar;
    c = toAscii(enc, ptr, end);
  }
  if (c != ASCII_QUOT && c != ASCII_APOS) {
    *nextTokPtr = ptr;
    return 0;
  }
  open = (char)c;
  ptr += enc->minBytesPerChar;
  *valPtr = ptr;
  for (;; ptr += enc->minBytesPerChar) {
    c = toAscii(enc, ptr, end);
    if (c == open)
      break;
    if (! (ASCII_a <= c && c <= ASCII_z) && ! (ASCII_A <= c && c <= ASCII_Z)
        && ! (ASCII_0 <= c && c <= ASCII_9) && c != ASCII_PERIOD
        && c != ASCII_MINUS && c != ASCII_UNDERSCORE) {
      *nextTokPtr = ptr;
      return 0;
    }
  }
  *nextTokPtr = ptr + enc->minBytesPerChar;
  return 1;
}