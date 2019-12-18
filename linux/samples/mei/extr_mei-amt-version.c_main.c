#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct amt_host_if {int dummy; } ;
struct amt_code_versions {unsigned int count; TYPE_3__* versions; } ;
struct TYPE_5__ {char* string; } ;
struct TYPE_4__ {char* string; } ;
struct TYPE_6__ {TYPE_2__ version; TYPE_1__ description; } ;

/* Variables and functions */
#define  AMT_STATUS_HOST_IF_EMPTY_RESPONSE 129 
#define  AMT_STATUS_SUCCESS 128 
 int amt_get_code_versions (struct amt_host_if*,struct amt_code_versions*) ; 
 int /*<<< orphan*/  amt_host_if_deinit (struct amt_host_if*) ; 
 int /*<<< orphan*/  amt_host_if_init (struct amt_host_if*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
	struct amt_code_versions ver;
	struct amt_host_if acmd;
	unsigned int i;
	uint32_t status;
	int ret;
	bool verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);

	if (!amt_host_if_init(&acmd, 5000, verbose)) {
		ret = 1;
		goto out;
	}

	status = amt_get_code_versions(&acmd, &ver);

	amt_host_if_deinit(&acmd);

	switch (status) {
	case AMT_STATUS_HOST_IF_EMPTY_RESPONSE:
		printf("Intel AMT: DISABLED\n");
		ret = 0;
		break;
	case AMT_STATUS_SUCCESS:
		printf("Intel AMT: ENABLED\n");
		for (i = 0; i < ver.count; i++) {
			printf("%s:\t%s\n", ver.versions[i].description.string,
				ver.versions[i].version.string);
		}
		ret = 0;
		break;
	default:
		printf("An error has occurred\n");
		ret = 1;
		break;
	}

out:
	return ret;
}