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
typedef  int /*<<< orphan*/  uint16_t ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int buf_write (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
buf_write_u16(struct buffer *dest, int data)
{
    uint16_t u16 = htons((uint16_t) data);
    return buf_write(dest, &u16, sizeof(uint16_t));
}