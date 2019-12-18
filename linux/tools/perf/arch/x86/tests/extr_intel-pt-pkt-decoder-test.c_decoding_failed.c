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
struct test_data {int /*<<< orphan*/  len; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void decoding_failed(struct test_data *d)
{
	pr_debug("Decoding failed!\n");
	pr_debug("Decoding:  ");
	dump_packet(&d->packet, d->bytes, d->len);
}