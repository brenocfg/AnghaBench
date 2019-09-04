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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcmf_core {void* base; int /*<<< orphan*/  id; } ;
struct brcmf_core_priv {struct brcmf_core pub; int /*<<< orphan*/  list; void* wrapbase; struct brcmf_chip_priv* chip; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  cores; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct brcmf_core* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct brcmf_core_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct brcmf_core *brcmf_chip_add_core(struct brcmf_chip_priv *ci,
					      u16 coreid, u32 base,
					      u32 wrapbase)
{
	struct brcmf_core_priv *core;

	core = kzalloc(sizeof(*core), GFP_KERNEL);
	if (!core)
		return ERR_PTR(-ENOMEM);

	core->pub.id = coreid;
	core->pub.base = base;
	core->chip = ci;
	core->wrapbase = wrapbase;

	list_add_tail(&core->list, &ci->cores);
	return &core->pub;
}