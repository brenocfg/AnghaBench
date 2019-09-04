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
struct sigmadsp_control {char* name; unsigned int num_bytes; int /*<<< orphan*/  head; int /*<<< orphan*/  samplerates; void* addr; } ;
struct sigmadsp {int /*<<< orphan*/  ctrl_list; } ;
struct sigma_fw_chunk_control {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; int /*<<< orphan*/  num_bytes; } ;
struct sigma_fw_chunk {int /*<<< orphan*/  samplerates; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  kfree (struct sigmadsp_control*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sigma_fw_validate_control_name (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int sigma_fw_load_control(struct sigmadsp *sigmadsp,
	const struct sigma_fw_chunk *chunk, unsigned int length)
{
	const struct sigma_fw_chunk_control *ctrl_chunk;
	struct sigmadsp_control *ctrl;
	unsigned int num_bytes;
	size_t name_len;
	char *name;
	int ret;

	if (length <= sizeof(*ctrl_chunk))
		return -EINVAL;

	ctrl_chunk = (const struct sigma_fw_chunk_control *)chunk;

	name_len = length - sizeof(*ctrl_chunk);
	if (name_len >= SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		name_len = SNDRV_CTL_ELEM_ID_NAME_MAXLEN - 1;

	/* Make sure there are no non-displayable characaters in the string */
	if (!sigma_fw_validate_control_name(ctrl_chunk->name, name_len))
		return -EINVAL;

	num_bytes = le16_to_cpu(ctrl_chunk->num_bytes);
	ctrl = kzalloc(sizeof(*ctrl) + num_bytes, GFP_KERNEL);
	if (!ctrl)
		return -ENOMEM;

	name = kzalloc(name_len + 1, GFP_KERNEL);
	if (!name) {
		ret = -ENOMEM;
		goto err_free_ctrl;
	}
	memcpy(name, ctrl_chunk->name, name_len);
	name[name_len] = '\0';
	ctrl->name = name;

	ctrl->addr = le16_to_cpu(ctrl_chunk->addr);
	ctrl->num_bytes = num_bytes;
	ctrl->samplerates = le32_to_cpu(chunk->samplerates);

	list_add_tail(&ctrl->head, &sigmadsp->ctrl_list);

	return 0;

err_free_ctrl:
	kfree(ctrl);

	return ret;
}