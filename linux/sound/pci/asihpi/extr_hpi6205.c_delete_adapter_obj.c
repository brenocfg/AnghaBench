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
struct hpi_hw_obj {scalar_t__* outstream_host_buffer_size; int /*<<< orphan*/ * outstream_host_buffers; scalar_t__* instream_host_buffer_size; int /*<<< orphan*/ * instream_host_buffers; int /*<<< orphan*/ * p_interface_buffer; int /*<<< orphan*/  h_locked_mem; int /*<<< orphan*/  p_cache; int /*<<< orphan*/  h_control_cache; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;

/* Variables and functions */
 int HPI_MAX_STREAMS ; 
 int /*<<< orphan*/  hpi_free_control_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpios_locked_mem_free (int /*<<< orphan*/ *) ; 
 scalar_t__ hpios_locked_mem_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hpi_hw_obj*) ; 

__attribute__((used)) static void delete_adapter_obj(struct hpi_adapter_obj *pao)
{
	struct hpi_hw_obj *phw = pao->priv;
	int i;

	if (hpios_locked_mem_valid(&phw->h_control_cache)) {
		hpios_locked_mem_free(&phw->h_control_cache);
		hpi_free_control_cache(phw->p_cache);
	}

	if (hpios_locked_mem_valid(&phw->h_locked_mem)) {
		hpios_locked_mem_free(&phw->h_locked_mem);
		phw->p_interface_buffer = NULL;
	}

	for (i = 0; i < HPI_MAX_STREAMS; i++)
		if (hpios_locked_mem_valid(&phw->instream_host_buffers[i])) {
			hpios_locked_mem_free(&phw->instream_host_buffers[i]);
			/*?phw->InStreamHostBuffers[i] = NULL; */
			phw->instream_host_buffer_size[i] = 0;
		}

	for (i = 0; i < HPI_MAX_STREAMS; i++)
		if (hpios_locked_mem_valid(&phw->outstream_host_buffers[i])) {
			hpios_locked_mem_free(&phw->outstream_host_buffers
				[i]);
			phw->outstream_host_buffer_size[i] = 0;
		}
	kfree(phw);
}