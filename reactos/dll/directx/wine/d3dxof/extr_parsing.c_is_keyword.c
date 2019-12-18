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
typedef  int /*<<< orphan*/  parse_buffer ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _strnicmp (char*,char const*,int) ; 
 scalar_t__ is_separator (char) ; 
 int /*<<< orphan*/  read_bytes (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rewind_bytes (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static BOOL is_keyword(parse_buffer* buf, const char* keyword)
{
  char tmp[8]; /* longest keyword size (template) */
  DWORD len = strlen(keyword);

  if (!read_bytes(buf, tmp, len))
    return FALSE;
  if (_strnicmp(tmp, keyword, len))
  {
    rewind_bytes(buf, len);
    return FALSE;
  }

  if (!read_bytes(buf, tmp, 1))
    return TRUE;
  if (is_separator(tmp[0]))
  {
    rewind_bytes(buf, 1);
    return TRUE;
  }
  rewind_bytes(buf, len+1);
  return FALSE;
}