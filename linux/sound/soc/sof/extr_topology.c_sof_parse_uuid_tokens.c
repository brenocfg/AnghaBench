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
struct sof_topology_token {scalar_t__ type; scalar_t__ token; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  (* get_token ) (struct snd_soc_tplg_vendor_uuid_elem*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct snd_soc_tplg_vendor_uuid_elem {int /*<<< orphan*/  token; } ;
struct snd_soc_tplg_vendor_array {struct snd_soc_tplg_vendor_uuid_elem* uuid; int /*<<< orphan*/  num_elems; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_TPLG_TUPLE_TYPE_UUID ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_tplg_vendor_uuid_elem*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sof_parse_uuid_tokens(struct snd_soc_component *scomp,
				  void *object,
				  const struct sof_topology_token *tokens,
				  int count,
				  struct snd_soc_tplg_vendor_array *array)
{
	struct snd_soc_tplg_vendor_uuid_elem *elem;
	int i, j;

	/* parse element by element */
	for (i = 0; i < le32_to_cpu(array->num_elems); i++) {
		elem = &array->uuid[i];

		/* search for token */
		for (j = 0; j < count; j++) {
			/* match token type */
			if (tokens[j].type != SND_SOC_TPLG_TUPLE_TYPE_UUID)
				continue;

			/* match token id */
			if (tokens[j].token != le32_to_cpu(elem->token))
				continue;

			/* matched - now load token */
			tokens[j].get_token(elem, object, tokens[j].offset,
					    tokens[j].size);
		}
	}
}