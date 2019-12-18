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
typedef  int /*<<< orphan*/  uint8_t ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * buf_prepend (struct buffer*,int) ; 
 int /*<<< orphan*/ * buf_write_alloc (struct buffer*,int) ; 

__attribute__((used)) static inline uint8_t *
buf_write_alloc_prepend(struct buffer *buf, int size, bool prepend)
{
    return prepend ? buf_prepend(buf, size) : buf_write_alloc(buf, size);
}