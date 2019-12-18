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
struct ip_vs_sync_buff {struct ip_vs_sync_buff* mesg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ip_vs_sync_buff*) ; 

__attribute__((used)) static inline void ip_vs_sync_buff_release(struct ip_vs_sync_buff *sb)
{
	kfree(sb->mesg);
	kfree(sb);
}