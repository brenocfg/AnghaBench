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
struct TYPE_2__ {unsigned long long offset; } ;
struct snd_dg00x {TYPE_1__ async_handler; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_unknown_message (struct snd_dg00x*,unsigned long long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_message(struct fw_card *card, struct fw_request *request,
			   int tcode, int destination, int source,
			   int generation, unsigned long long offset,
			   void *data, size_t length, void *callback_data)
{
	struct snd_dg00x *dg00x = callback_data;
	__be32 *buf = (__be32 *)data;

	fw_send_response(card, request, RCODE_COMPLETE);

	if (offset == dg00x->async_handler.offset)
		handle_unknown_message(dg00x, offset, buf);
}