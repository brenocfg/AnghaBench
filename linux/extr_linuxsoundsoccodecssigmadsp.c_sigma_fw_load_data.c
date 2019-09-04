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
struct sigmadsp_data {unsigned int length; int /*<<< orphan*/  head; int /*<<< orphan*/  data; int /*<<< orphan*/  samplerates; int /*<<< orphan*/  addr; } ;
struct sigmadsp {int /*<<< orphan*/  data_list; } ;
struct sigma_fw_chunk_data {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct sigma_fw_chunk {int /*<<< orphan*/  samplerates; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sigmadsp_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sigma_fw_load_data(struct sigmadsp *sigmadsp,
	const struct sigma_fw_chunk *chunk, unsigned int length)
{
	const struct sigma_fw_chunk_data *data_chunk;
	struct sigmadsp_data *data;

	if (length <= sizeof(*data_chunk))
		return -EINVAL;

	data_chunk = (struct sigma_fw_chunk_data *)chunk;

	length -= sizeof(*data_chunk);

	data = kzalloc(sizeof(*data) + length, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->addr = le16_to_cpu(data_chunk->addr);
	data->length = length;
	data->samplerates = le32_to_cpu(chunk->samplerates);
	memcpy(data->data, data_chunk->data, length);
	list_add_tail(&data->head, &sigmadsp->data_list);

	return 0;
}