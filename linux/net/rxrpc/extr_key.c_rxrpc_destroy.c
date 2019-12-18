#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxrpc_free_token_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_destroy(struct key *key)
{
	rxrpc_free_token_list(key->payload.data[0]);
}