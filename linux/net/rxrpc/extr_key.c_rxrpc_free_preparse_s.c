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
struct TYPE_2__ {scalar_t__* data; } ;
struct key_preparsed_payload {TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_skcipher (scalar_t__) ; 

__attribute__((used)) static void rxrpc_free_preparse_s(struct key_preparsed_payload *prep)
{
	if (prep->payload.data[0])
		crypto_free_skcipher(prep->payload.data[0]);
}