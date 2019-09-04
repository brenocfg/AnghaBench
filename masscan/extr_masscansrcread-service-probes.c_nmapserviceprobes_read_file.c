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
struct NmapServiceProbeList {unsigned int line_number; scalar_t__ filename; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 struct NmapServiceProbeList* nmapserviceprobes_new (char const*) ; 
 int /*<<< orphan*/  nmapserviceprobes_print (struct NmapServiceProbeList*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_line (struct NmapServiceProbeList*,char*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stdout ; 

struct NmapServiceProbeList *
nmapserviceprobes_read_file(const char *filename)
{
    FILE *fp;
    char line[32768];
    struct NmapServiceProbeList *result;
    
    /*
     * Open the file
     */
    fp = fopen(filename, "rt");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }

    /*
     * Create the result structure
     */
    result = nmapserviceprobes_new(filename);
    
    /*
     * parse all lines in the text file
     */
    while (fgets(line, sizeof(line), fp)) {

        /* Track line number for error messages */
        result->line_number++;

        /* Parse this string into a record */
        parse_line(result, line);
    }
    
    fclose(fp);
    result->filename = 0; /* name no longer valid after this point */
    result->line_number = (unsigned)~0; /* line number no longer valid after this point */
    
    nmapserviceprobes_print(result, stdout);
    
    return result;
}