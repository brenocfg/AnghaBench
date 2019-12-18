#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nb_target_deps; int /*<<< orphan*/  target_deps; } ;
typedef  TYPE_1__ TCCState ;

/* Variables and functions */
 int AFF_PREPROCESS ; 
 int AFF_PRINT_ERROR ; 
 int /*<<< orphan*/  PATHCMP (char const*,char*) ; 
 int /*<<< orphan*/  dynarray_add (void***,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  tcc_close () ; 
 int tcc_compile (TYPE_1__*) ; 
 int /*<<< orphan*/  tcc_error (char*,...) ; 
 char* tcc_fileextension (char const*) ; 
 int tcc_open (TYPE_1__*,char const*) ; 
 int tcc_preprocess (TYPE_1__*) ; 

int tcc_add_file_internal(TCCState *s1, const char *filename, int flags)
{
	const char *ext;
	int ret;

	/* find source file type with extension */
	ext = tcc_fileextension (filename);
	if (ext[0]) {
		ext++;
	}

	/* open the file */
	ret = tcc_open (s1, filename);
	if (ret < 0) {
		if (flags & AFF_PRINT_ERROR) {
			tcc_error ("file '%s' not found", filename);
		}
		return ret;
	}

	/* update target deps */
	dynarray_add ((void ***) &s1->target_deps, &s1->nb_target_deps,
		strdup (filename));

	if (flags & AFF_PREPROCESS) {
		ret = tcc_preprocess (s1);
		goto the_end;
	}

	if (!ext[0] || !PATHCMP (ext, "c") || !PATHCMP (ext, "h") || !PATHCMP (ext, "cparse")) {
		/* C file assumed */
		ret = tcc_compile (s1);
		goto the_end;
	}
	if (ret < 0) {
		tcc_error ("unrecognized file type");
	}

the_end:
	tcc_close ();
	return ret;
}