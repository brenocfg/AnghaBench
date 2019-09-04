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
struct tun_struct {int /*<<< orphan*/  dev; } ;
struct tun_file {int napi_enabled; int napi_frags_enabled; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_napi_poll ; 

__attribute__((used)) static void tun_napi_init(struct tun_struct *tun, struct tun_file *tfile,
			  bool napi_en, bool napi_frags)
{
	tfile->napi_enabled = napi_en;
	tfile->napi_frags_enabled = napi_en && napi_frags;
	if (napi_en) {
		netif_napi_add(tun->dev, &tfile->napi, tun_napi_poll,
			       NAPI_POLL_WEIGHT);
		napi_enable(&tfile->napi);
	}
}