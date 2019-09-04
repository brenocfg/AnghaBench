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
struct d3dcompiler_shader_reflection {int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_dword (char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT d3dcompiler_parse_shdr(struct d3dcompiler_shader_reflection *r, const char *data, DWORD data_size)
{
    const char *ptr = data;

    read_dword(&ptr, &r->version);
    TRACE("Shader version: %u\n", r->version);

    /* todo: Check if anything else is needed from the shdr or shex blob. */

    return S_OK;
}