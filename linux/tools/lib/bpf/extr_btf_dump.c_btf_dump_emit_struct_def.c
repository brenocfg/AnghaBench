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
struct btf_type {scalar_t__ name_off; } ;
struct btf_member {int /*<<< orphan*/  type; int /*<<< orphan*/  name_off; } ;
struct btf_dump {int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  btf__resolve_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_align_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_dump_emit_bit_padding (struct btf_dump*,int,int,int,int,int) ; 
 int /*<<< orphan*/  btf_dump_emit_type_decl (struct btf_dump*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  btf_dump_printf (struct btf_dump*,char*,...) ; 
 int /*<<< orphan*/  btf_dump_type_name (struct btf_dump*,int /*<<< orphan*/ ) ; 
 int btf_is_struct (struct btf_type const*) ; 
 int btf_is_struct_packed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btf_type const*) ; 
 int btf_member_bit_offset (struct btf_type const*,int) ; 
 int btf_member_bitfield_size (struct btf_type const*,int) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 
 char* btf_name_of (struct btf_dump*,int /*<<< orphan*/ ) ; 
 int btf_vlen (struct btf_type const*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfx (int) ; 

__attribute__((used)) static void btf_dump_emit_struct_def(struct btf_dump *d,
				     __u32 id,
				     const struct btf_type *t,
				     int lvl)
{
	const struct btf_member *m = btf_members(t);
	bool is_struct = btf_is_struct(t);
	int align, i, packed, off = 0;
	__u16 vlen = btf_vlen(t);

	packed = is_struct ? btf_is_struct_packed(d->btf, id, t) : 0;
	align = packed ? 1 : btf_align_of(d->btf, id);

	btf_dump_printf(d, "%s%s%s {",
			is_struct ? "struct" : "union",
			t->name_off ? " " : "",
			btf_dump_type_name(d, id));

	for (i = 0; i < vlen; i++, m++) {
		const char *fname;
		int m_off, m_sz;

		fname = btf_name_of(d, m->name_off);
		m_sz = btf_member_bitfield_size(t, i);
		m_off = btf_member_bit_offset(t, i);
		align = packed ? 1 : btf_align_of(d->btf, m->type);

		btf_dump_emit_bit_padding(d, off, m_off, m_sz, align, lvl + 1);
		btf_dump_printf(d, "\n%s", pfx(lvl + 1));
		btf_dump_emit_type_decl(d, m->type, fname, lvl + 1);

		if (m_sz) {
			btf_dump_printf(d, ": %d", m_sz);
			off = m_off + m_sz;
		} else {
			m_sz = max(0, btf__resolve_size(d->btf, m->type));
			off = m_off + m_sz * 8;
		}
		btf_dump_printf(d, ";");
	}

	if (vlen)
		btf_dump_printf(d, "\n");
	btf_dump_printf(d, "%s}", pfx(lvl));
	if (packed)
		btf_dump_printf(d, " __attribute__((packed))");
}