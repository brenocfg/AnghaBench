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
struct d3dcompiler_shader_reflection_type_member {int offset; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct d3dcompiler_shader_reflection {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  copy_name (char const*,int /*<<< orphan*/ *) ; 
 int debugstr_a (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reflection_type (struct d3dcompiler_shader_reflection*,char const*,int) ; 
 int /*<<< orphan*/  read_dword (char const**,int*) ; 

__attribute__((used)) static HRESULT d3dcompiler_parse_type_members(struct d3dcompiler_shader_reflection *ref,
        struct d3dcompiler_shader_reflection_type_member *member, const char *data, const char **ptr)
{
    DWORD offset;

    read_dword(ptr, &offset);
    if (!copy_name(data + offset, &member->name))
    {
        ERR("Failed to copy name.\n");
        return E_OUTOFMEMORY;
    }
    TRACE("Member name: %s.\n", debugstr_a(member->name));

    read_dword(ptr, &offset);
    TRACE("Member type offset: %x\n", offset);

    member->type = get_reflection_type(ref, data, offset);
    if (!member->type)
    {
        ERR("Failed to get member type\n");
        HeapFree(GetProcessHeap(), 0, member->name);
        return E_FAIL;
    }

    read_dword(ptr, &member->offset);
    TRACE("Member offset %x\n", member->offset);

    return S_OK;
}