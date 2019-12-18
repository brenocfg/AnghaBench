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
struct TYPE_3__ {scalar_t__ rem_bytes; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ parse_buffer ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL read_bytes(parse_buffer * buf, LPVOID data, DWORD size)
{
  if (buf->rem_bytes < size)
    return FALSE;
  memcpy(data, buf->buffer, size);
  buf->buffer += size;
  buf->rem_bytes -= size;
  return TRUE;
}