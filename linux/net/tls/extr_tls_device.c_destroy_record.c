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
struct tls_record_info {int num_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_frag_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tls_record_info*) ; 

__attribute__((used)) static void destroy_record(struct tls_record_info *record)
{
	int i;

	for (i = 0; i < record->num_frags; i++)
		__skb_frag_unref(&record->frags[i]);
	kfree(record);
}