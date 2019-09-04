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
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  GD_NOTICE ; 
 int GetDataBlock_ (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 scalar_t__ VERBOSE ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  gd_error_ex (int /*<<< orphan*/ ,char*,int,char*) ; 
 char* safe_emalloc (int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static int
GetDataBlock(gdIOCtx *fd, unsigned char *buf, int *ZeroDataBlockP)
{
	int rv;
	int i;

	rv = GetDataBlock_(fd,buf, ZeroDataBlockP);
	if (VERBOSE) {
		char *tmp = NULL;
		if (rv > 0) {
			tmp = safe_emalloc(3 * rv, sizeof(char), 1);
			for (i=0;i<rv;i++) {
				sprintf(&tmp[3*sizeof(char)*i], " %02x", buf[i]);
			}
		} else {
			tmp = estrdup("");
		}
		gd_error_ex(GD_NOTICE, "[GetDataBlock returning %d: %s]", rv, tmp);
		efree(tmp);
	}
	return(rv);
}