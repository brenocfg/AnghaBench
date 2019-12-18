#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct address_space {int dummy; } ;
struct gfs2_sbd {struct address_space sd_aspace; } ;
struct TYPE_2__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (struct address_space*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_io_error (struct gfs2_sbd*) ; 

__attribute__((used)) static void gfs2_meta_sync(struct gfs2_glock *gl)
{
	struct address_space *mapping = gfs2_glock2aspace(gl);
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	int error;

	if (mapping == NULL)
		mapping = &sdp->sd_aspace;

	filemap_fdatawrite(mapping);
	error = filemap_fdatawait(mapping);

	if (error)
		gfs2_io_error(gl->gl_name.ln_sbd);
}