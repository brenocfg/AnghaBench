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
struct Output {scalar_t__ when_scan_started; } ;
struct Masscan {int /*<<< orphan*/  banner_types; int /*<<< orphan*/  ports; int /*<<< orphan*/  targets; } ;

/* Variables and functions */
 struct Output* output_create (struct Masscan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_destroy (struct Output*) ; 
 int /*<<< orphan*/  parse_file (struct Output*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
read_binary_scanfile(struct Masscan *masscan,
                     int arg_first, int arg_max, char *argv[])
{
    struct Output *out;
    int i;

    //readscan_report_init();


    out = output_create(masscan, 0);
    
    /*
     * Set the start time to zero. We'll read it from the first file
     * that we parse
     */
    out->when_scan_started = 0;

    /*
     * We don't parse the entire argument list, just a subrange
     * containing the list of files. The 'arg_first' parameter
     * points to the first filename after the '--readscan'
     * parameter, and 'arg_max' is the parameter after
     * the last filename. For example, consider an argument list that
     * looks like:
     *   masscan --foo --readscan file1.scan file2.scan --bar
     * Then arg_first=3 and arg_max=5.
     */
    for (i=arg_first; i<arg_max; i++) {
        parse_file(out, argv[i], &masscan->targets, &masscan->ports,
                   &masscan->banner_types);
    }

    output_destroy(out);

    //readscan_report_print();

}