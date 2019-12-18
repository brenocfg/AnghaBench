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
typedef  size_t u32 ;
struct tipc_msg {int /*<<< orphan*/ * hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (size_t) ; 

__attribute__((used)) static inline void msg_set_word(struct tipc_msg *m, u32 w, u32 val)
{
	m->hdr[w] = htonl(val);
}