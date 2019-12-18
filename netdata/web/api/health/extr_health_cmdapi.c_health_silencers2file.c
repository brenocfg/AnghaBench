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
struct TYPE_3__ {scalar_t__ len; char* buffer; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  silencers_filename ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void health_silencers2file(BUFFER *wb) {
    if (wb->len == 0) return;

    FILE *fd = fopen(silencers_filename, "wb");
    if(fd) {
        size_t written = (size_t)fprintf(fd, "%s", wb->buffer) ;
        if (written == wb->len ) {
            info("Silencer changes written to %s", silencers_filename);
        }
        fclose(fd);
        return;
    }
    error("Silencer changes could not be written to %s. Error %s", silencers_filename, strerror(errno));
}