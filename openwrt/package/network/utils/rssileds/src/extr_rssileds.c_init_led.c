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
struct stat {int dummy; } ;
struct led {char* sysfspath; int /*<<< orphan*/ * controlfd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* LEDS_BASEPATH ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ set_led (struct led*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

int init_led(struct led **led, char *ledname)
{
	struct led *newled;
	struct stat statbuffer;
	int status;
	char *bp;
	FILE *bfp;

	bp = calloc(sizeof(char), strlen(ledname) + strlen(LEDS_BASEPATH) + 12);
	if ( ! bp )
		goto return_error;

	sprintf(bp, "%s%s/brightness", LEDS_BASEPATH, ledname);

	status = stat(bp, &statbuffer);
	if ( status )
		goto cleanup_fname;

	bfp = fopen( bp, "w" );
	if ( !bfp )
		goto cleanup_fname;

	if ( ferror(bfp) )
		goto cleanup_fp;

	/* sysfs path exists and, allocate LED struct */
	newled = calloc(sizeof(struct led),1);
	if ( !newled )
		goto cleanup_fp;

	newled->sysfspath = bp;
	newled->controlfd = bfp;

	*led = newled;

	if ( set_led(newled, 255) )
		goto cleanup_fp;

	if ( set_led(newled, 0) )
		goto cleanup_fp;

	return 0;

cleanup_fp:
	fclose(bfp);
cleanup_fname:
	free(bp);
return_error:
	syslog(LOG_CRIT, "can't open LED %s\n", ledname);
	*led = NULL;
	return -1;
}