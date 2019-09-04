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
struct hpi_response {int dummy; } ;
struct hpi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_CLOSE ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HPI_OBJ_ADAPTER ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adapter_close(struct hpi_message *phm, struct hpi_response *phr)
{
	HPI_DEBUG_LOG(VERBOSE, "adapter_close\n");
	hpi_init_response(phr, HPI_OBJ_ADAPTER, HPI_ADAPTER_CLOSE, 0);
}