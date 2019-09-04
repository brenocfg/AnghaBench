#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  c_strcat (char*,char const*) ; 
 int /*<<< orphan*/  c_strcpy (char*,char*) ; 
 size_t c_strcspn (char const*,char*) ; 
 size_t c_strlen (char const*) ; 
 int /*<<< orphan*/  c_strncat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  c_strncpy (char*,char const*,size_t) ; 

void luaO_chunkid (char *out, const char *source, size_t bufflen) {
  if (*source == '=') {
    c_strncpy(out, source+1, bufflen);  /* remove first char */
    out[bufflen-1] = '\0';  /* ensures null termination */
  }
  else {  /* out = "source", or "...source" */
    if (*source == '@') {
      size_t l;
      source++;  /* skip the `@' */
      bufflen -= sizeof(" '...' ");
      l = c_strlen(source);
      c_strcpy(out, "");
      if (l > bufflen) {
        source += (l-bufflen);  /* get last part of file name */
        c_strcat(out, "...");
      }
      c_strcat(out, source);
    }
    else {  /* out = [string "string"] */
      size_t len = c_strcspn(source, "\n\r");  /* stop at first newline */
      bufflen -= sizeof(" [string \"...\"] ");
      if (len > bufflen) len = bufflen;
      c_strcpy(out, "[string \"");
      if (source[len] != '\0') {  /* must truncate? */
        c_strncat(out, source, len);
        c_strcat(out, "...");
      }
      else
        c_strcat(out, source);
      c_strcat(out, "\"]");
    }
  }
}