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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int rem_bytes; char* buffer; scalar_t__ value; } ;
typedef  TYPE_1__ parse_buffer ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  is_separator (char) ; 
 size_t min (int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static BOOL is_name(parse_buffer* buf)
{
  char tmp[512];
  DWORD pos = 0;
  char c;
  BOOL error = FALSE;
  while (pos < buf->rem_bytes && !is_separator(c = *(buf->buffer+pos)))
  {
    if (!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')) || (c == '_') || (c == '-')))
      error = TRUE;
    if (pos < sizeof(tmp))
        tmp[pos] = c;
    pos++;
  }
  tmp[min(pos, sizeof(tmp) - 1)] = 0;

  if (error)
  {
    TRACE("Wrong name %s\n", tmp);
    return FALSE;
  }

  buf->buffer += pos;
  buf->rem_bytes -= pos;

  TRACE("Found name %s\n", tmp);
  strcpy((char*)buf->value, tmp);

  return TRUE;
}