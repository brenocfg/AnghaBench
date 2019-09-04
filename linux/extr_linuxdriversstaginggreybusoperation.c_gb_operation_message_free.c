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
struct gb_message {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_message_cache ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gb_message*) ; 

__attribute__((used)) static void gb_operation_message_free(struct gb_message *message)
{
	kfree(message->buffer);
	kmem_cache_free(gb_message_cache, message);
}