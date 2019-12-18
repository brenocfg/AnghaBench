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
typedef  int /*<<< orphan*/  uint32_t ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int buf_write (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
buf_write_u32(struct buffer *dest, int data)
{
    uint32_t u32 = htonl((uint32_t) data);
    return buf_write(dest, &u32, sizeof(uint32_t));
}