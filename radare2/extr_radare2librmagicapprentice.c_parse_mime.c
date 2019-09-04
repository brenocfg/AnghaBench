#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
struct r_magic_entry {int cont_count; struct r_magic* mp; } ;
struct r_magic {char* mimetype; char* desc; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ RMagic ;

/* Variables and functions */
 int /*<<< orphan*/  EATAB ; 
 int R_MAGIC_CHECK ; 
 int /*<<< orphan*/  file_error (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  file_magwarn (TYPE_1__*,char*,char*,size_t) ; 
 scalar_t__ isalnum (int /*<<< orphan*/ ) ; 
 scalar_t__ isascii (int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char const) ; 

__attribute__((used)) static int parse_mime(RMagic *ms, struct r_magic_entry **mentryp, ut32 *nmentryp, const char *line) {
	size_t i;
	const char *l = line;
	struct r_magic *m;
	struct r_magic_entry *me;

	if (*nmentryp == 0) {
		file_error(ms, 0, "No current entry for MIME type");
		return -1;
	}

	me = &(*mentryp)[*nmentryp - 1];
	m = &me->mp[me->cont_count == 0 ? 0 : me->cont_count - 1];

	if (m->mimetype[0] != '\0') {
		file_error(ms, 0, "Current entry already has a MIME type: %s\n"
		    "Description: %s\nNew type: %s", m->mimetype, m->desc, l);
		return -1;
	}

	EATAB;
	for (i = 0;
		*l && ((isascii ((ut8)*l) && isalnum ((ut8)*l)) || strchr ("-+/.", *l)) && i < sizeof (m->mimetype);
		m->mimetype[i++] = *l++) {}
	if (i == sizeof (m->mimetype)) {
		m->desc[sizeof (m->mimetype) - 1] = '\0';
		if (ms->flags & R_MAGIC_CHECK) {
			file_magwarn (ms, "MIME type `%s' truncated %zu",
				m->mimetype, i);
		}
	} else {
		m->mimetype[i] = '\0';
	}

	return (i>0)? 0: -1;
}