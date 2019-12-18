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
struct TYPE_3__ {char* buf; size_t size; scalar_t__ pos; } ;
typedef  TYPE_1__ cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (char*) ; 
 scalar_t__ malloc (size_t) ; 

cursor_t cursor_create(size_t size)
{
  cursor_t cursor;
  cursor.buf = (char*)malloc(size);
  cursor.size = size;
  cursor.pos = 0;
  FUZZ_ASSERT(cursor.buf);
  return cursor;
}