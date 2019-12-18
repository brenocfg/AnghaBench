#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut32 ;
struct TYPE_3__ {char* string; } ;
typedef  int /*<<< orphan*/  RListFree ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  TYPE_1__ RBinString ;
typedef  int /*<<< orphan*/  RBinSection ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/ * newSection (char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parseStrings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ r_bin_section_free ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* r_list_get_n (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 
 scalar_t__ r_read_le32 (char*) ; 
 int /*<<< orphan*/  stringsBeginAt ; 

__attribute__((used)) static RList *parseSections(RBuffer *b, int x, int n_sections, RList *strings) {
	// eprintf ("Sections\n");
	int buf_sz = r_buf_size (b);
	char *buf = malloc (buf_sz);
	if (!buf) {
		return NULL;
	}
	bool must_free = false;
	if (!strings) {
		strings = parseStrings (b, stringsBeginAt, buf_sz);
		if (strings) {
			must_free = true;
		}
	}
	// hack
	r_buf_read_at (b, x, (ut8 *)buf, 4);
	if (buf[0] == '_') {
		x += 16;
	}
	RList *res = r_list_newf ((RListFree)r_bin_section_free);
	int i;
	r_buf_read_at (b, x, (ut8 *)buf, buf_sz);
	int off = 0;
	for (i = 0; i < n_sections; i++) {
		off = i * 16;
		if (off + 8 >= buf_sz) {
			break;
		}
		RBinString *name = strings? r_list_get_n (strings, i): NULL;
		const char *namestr = name? name->string: "";
		ut32 A = r_read_le32 (buf + off);
		ut32 B = r_read_le32 (buf + off + 4);
		//ut32 C = r_read_le32 (buf + off + 8);
		// ut32 D = r_read_le32 (buf + off + 12);
		// eprintf ("0x%08"PFMT64x"  addr=0x%08x size=0x%08x unk=0x%08x zero=0x%08x  %s\n",
		//	(ut64)x + i + off, A, B, C, D, namestr);
		RBinSection *section = newSection (namestr, A, A + B, 0);
		r_list_append (res, section);
	}
	if (must_free) {
		r_list_free (strings);
	}
	free (buf);
	return res;
}