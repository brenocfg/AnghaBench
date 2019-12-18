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
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_probe_map_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  skips ; 

__attribute__((used)) static bool skip_unsupported_map(enum bpf_map_type map_type)
{
	if (!bpf_probe_map_type(map_type, 0)) {
		printf("SKIP (unsupported map type %d)\n", map_type);
		skips++;
		return true;
	}
	return false;
}