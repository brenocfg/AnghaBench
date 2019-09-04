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
struct pcmcia_device {int /*<<< orphan*/  func; int /*<<< orphan*/  socket; } ;
struct pcmcia_cfg_mem {int (* conf_check ) (struct pcmcia_device*,void*) ;int /*<<< orphan*/  parse; void* priv_data; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_CFTABLE_ENTRY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct pcmcia_cfg_mem*) ; 
 struct pcmcia_cfg_mem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pccard_loop_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pcmcia_cfg_mem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_do_loop_config ; 

int pcmcia_loop_config(struct pcmcia_device *p_dev,
		       int	(*conf_check)	(struct pcmcia_device *p_dev,
						 void *priv_data),
		       void *priv_data)
{
	struct pcmcia_cfg_mem *cfg_mem;
	int ret;

	cfg_mem = kzalloc(sizeof(struct pcmcia_cfg_mem), GFP_KERNEL);
	if (cfg_mem == NULL)
		return -ENOMEM;

	cfg_mem->p_dev = p_dev;
	cfg_mem->conf_check = conf_check;
	cfg_mem->priv_data = priv_data;

	ret = pccard_loop_tuple(p_dev->socket, p_dev->func,
				CISTPL_CFTABLE_ENTRY, &cfg_mem->parse,
				cfg_mem, pcmcia_do_loop_config);

	kfree(cfg_mem);
	return ret;
}