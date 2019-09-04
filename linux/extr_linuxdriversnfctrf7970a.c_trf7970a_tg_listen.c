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
typedef  int /*<<< orphan*/  u16 ;
struct trf7970a {int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct nfc_digital_dev {int dummy; } ;
typedef  int /*<<< orphan*/  nfc_digital_cmd_complete_t ;

/* Variables and functions */
 int _trf7970a_tg_listen (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trf7970a* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 

__attribute__((used)) static int trf7970a_tg_listen(struct nfc_digital_dev *ddev, u16 timeout,
			      nfc_digital_cmd_complete_t cb, void *arg)
{
	struct trf7970a *trf = nfc_digital_get_drvdata(ddev);

	dev_dbg(trf->dev, "Listen - state: %d, timeout: %d ms\n",
		trf->state, timeout);

	return _trf7970a_tg_listen(ddev, timeout, cb, arg, false);
}