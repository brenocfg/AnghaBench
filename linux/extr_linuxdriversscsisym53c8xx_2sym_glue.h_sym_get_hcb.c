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
struct sym_hcb {int dummy; } ;
struct sym_data {struct sym_hcb* ncb; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sym_hcb * sym_get_hcb(struct Scsi_Host *host)
{
	return ((struct sym_data *)host->hostdata)->ncb;
}