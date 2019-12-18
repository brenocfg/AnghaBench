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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; struct skl_module_cfg* priv; } ;
struct skl_pipe_params {int dummy; } ;
struct skl_module_cfg {int /*<<< orphan*/  params_fixup; TYPE_1__* pipe; } ;
struct skl_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int conn_type; struct skl_pipe_params* p_params; } ;

/* Variables and functions */
 int SKL_PIPE_CONN_TYPE_FE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_dump_mconfig (struct skl_dev*,struct skl_module_cfg*) ; 
 int /*<<< orphan*/  skl_tplg_update_buffer_size (struct skl_dev*,struct skl_module_cfg*) ; 
 int /*<<< orphan*/  skl_tplg_update_params_fixup (struct skl_module_cfg*,struct skl_pipe_params*,int) ; 

__attribute__((used)) static void skl_tplg_update_module_params(struct snd_soc_dapm_widget *w,
							struct skl_dev *skl)
{
	struct skl_module_cfg *m_cfg = w->priv;
	struct skl_pipe_params *params = m_cfg->pipe->p_params;
	int p_conn_type = m_cfg->pipe->conn_type;
	bool is_fe;

	if (!m_cfg->params_fixup)
		return;

	dev_dbg(skl->dev, "Mconfig for widget=%s BEFORE updation\n",
				w->name);

	skl_dump_mconfig(skl, m_cfg);

	if (p_conn_type == SKL_PIPE_CONN_TYPE_FE)
		is_fe = true;
	else
		is_fe = false;

	skl_tplg_update_params_fixup(m_cfg, params, is_fe);
	skl_tplg_update_buffer_size(skl, m_cfg);

	dev_dbg(skl->dev, "Mconfig for widget=%s AFTER updation\n",
				w->name);

	skl_dump_mconfig(skl, m_cfg);
}