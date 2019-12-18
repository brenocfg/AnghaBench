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
struct nid_path {int depth; int /*<<< orphan*/ * idx; int /*<<< orphan*/ * path; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int HDA_COMPOSE_AMP_VAL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 scalar_t__ check_boost_vol (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int look_for_boost_amp(struct hda_codec *codec,
				       struct nid_path *path)
{
	unsigned int val = 0;
	hda_nid_t nid;
	int depth;

	for (depth = 0; depth < 3; depth++) {
		if (depth >= path->depth - 1)
			break;
		nid = path->path[depth];
		if (depth && check_boost_vol(codec, nid, HDA_OUTPUT, 0)) {
			val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
			break;
		} else if (check_boost_vol(codec, nid, HDA_INPUT,
					   path->idx[depth])) {
			val = HDA_COMPOSE_AMP_VAL(nid, 3, path->idx[depth],
						  HDA_INPUT);
			break;
		}
	}

	return val;
}