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
struct nfsd4_fs_locations {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
fsloc_parse(char **mesg, char *buf, struct nfsd4_fs_locations *fsloc){return 0;}