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
typedef  int /*<<< orphan*/  u8 ;
struct sdio_func {int dummy; } ;
struct ks_sdio_card {int /*<<< orphan*/  priv; } ;
struct TYPE_2__ {void* event; void* size; } ;
struct hostif_stop_request {TYPE_1__ header; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HIF_STOP_REQ ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 int /*<<< orphan*/  kfree (struct hostif_stop_request*) ; 
 struct hostif_stop_request* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 struct ks_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  write_to_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_stop_request(struct sdio_func *func)
{
	struct hostif_stop_request *pp;
	struct ks_sdio_card *card;
	size_t size;

	card = sdio_get_drvdata(func);

	pp = kzalloc(hif_align_size(sizeof(*pp)), GFP_KERNEL);
	if (!pp)
		return -ENOMEM;

	size = sizeof(*pp) - sizeof(pp->header.size);
	pp->header.size = cpu_to_le16(size);
	pp->header.event = cpu_to_le16(HIF_STOP_REQ);

	sdio_claim_host(func);
	write_to_device(card->priv, (u8 *)pp, hif_align_size(sizeof(*pp)));
	sdio_release_host(func);

	kfree(pp);
	return 0;
}