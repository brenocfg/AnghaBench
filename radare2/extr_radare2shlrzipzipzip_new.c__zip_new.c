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
struct zip_error {int dummy; } ;
struct zip {int /*<<< orphan*/ * tempdir; int /*<<< orphan*/ * file; scalar_t__ nfile_alloc; scalar_t__ nfile; int /*<<< orphan*/ * entry; scalar_t__ nentry_alloc; scalar_t__ nentry; scalar_t__ comment_changed; int /*<<< orphan*/ * comment_changes; int /*<<< orphan*/  comment_orig; int /*<<< orphan*/ * default_password; scalar_t__ ch_flags; scalar_t__ flags; int /*<<< orphan*/  error; scalar_t__ open_flags; int /*<<< orphan*/ * zp; int /*<<< orphan*/ * zn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 

struct zip *
_zip_new(struct zip_error *error)
{
    struct zip *za;

    za = (struct zip *)malloc(sizeof(struct zip));
    if (!za) {
	_zip_error_set(error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    za->zn = NULL;
    za->zp = NULL;
    za->open_flags = 0;
    _zip_error_init(&za->error);
    za->flags = za->ch_flags = 0;
    za->default_password = NULL;
    za->comment_orig = za->comment_changes = NULL;
    za->comment_changed = 0;
    za->nentry = za->nentry_alloc = 0;
    za->entry = NULL;
    za->nfile = za->nfile_alloc = 0;
    za->file = NULL;
    za->tempdir = NULL;
    
    return za;
}