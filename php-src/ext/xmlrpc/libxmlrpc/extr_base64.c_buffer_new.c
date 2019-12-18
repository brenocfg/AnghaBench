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
struct buffer_st {int length; scalar_t__ offset; scalar_t__* data; scalar_t__* ptr; } ;

/* Variables and functions */
 scalar_t__* emalloc (int) ; 

void buffer_new(struct buffer_st *b)
{
  b->length = 512;
  b->data = emalloc(sizeof(char)*(b->length));
  b->data[0] = 0;
  b->ptr = b->data;
  b->offset = 0;
}