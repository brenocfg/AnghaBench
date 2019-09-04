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
typedef  int /*<<< orphan*/  u32 ;
struct media_pad {int dummy; } ;
struct media_entity {int dummy; } ;
struct imx_media_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct media_pad* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct media_pad* find_pipeline_pad (struct imx_media_dev*,struct media_entity*,int /*<<< orphan*/ ,int) ; 

struct media_pad *
imx_media_find_upstream_pad(struct imx_media_dev *imxmd,
			    struct media_entity *start_entity,
			    u32 grp_id)
{
	struct media_pad *pad;

	pad = find_pipeline_pad(imxmd, start_entity, grp_id, true);
	if (!pad)
		return ERR_PTR(-ENODEV);

	return pad;
}