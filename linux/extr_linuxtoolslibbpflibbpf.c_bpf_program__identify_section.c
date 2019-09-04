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
struct bpf_program {int /*<<< orphan*/  section_name; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int libbpf_prog_type_by_name (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int
bpf_program__identify_section(struct bpf_program *prog,
			      enum bpf_prog_type *prog_type,
			      enum bpf_attach_type *expected_attach_type)
{
	return libbpf_prog_type_by_name(prog->section_name, prog_type,
					expected_attach_type);
}