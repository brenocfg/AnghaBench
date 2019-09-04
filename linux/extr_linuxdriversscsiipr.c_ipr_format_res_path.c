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
typedef  int /*<<< orphan*/  u8 ;
struct ipr_ioa_cfg {TYPE_1__* host; } ;
struct TYPE_2__ {int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipr_format_res_path (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *ipr_format_res_path(struct ipr_ioa_cfg *ioa_cfg,
				 u8 *res_path, char *buffer, int len)
{
	char *p = buffer;

	*p = '\0';
	p += snprintf(p, buffer + len - p, "%d/", ioa_cfg->host->host_no);
	__ipr_format_res_path(res_path, p, len - (buffer - p));
	return buffer;
}