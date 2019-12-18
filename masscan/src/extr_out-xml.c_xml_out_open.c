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
struct TYPE_2__ {char* stylesheet; } ;
struct Output {TYPE_1__ xml; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xml_out_open(struct Output *out, FILE *fp)
{
    //const struct Masscan *masscan = out->masscan;

    fprintf(fp, "<?xml version=\"1.0\"?>\r\n");
    fprintf(fp, "<!-- masscan v1.0 scan -->\r\n");
    if (out->xml.stylesheet && out->xml.stylesheet[0]) {
        fprintf(fp, "<?xml-stylesheet href=\"%s\" type=\"text/xsl\"?>\r\n",
            out->xml.stylesheet);
    }
    fprintf(fp, "<nmaprun scanner=\"%s\" start=\"%u\" version=\"%s\"  xmloutputversion=\"%s\">\r\n",
        "masscan",
        (unsigned)time(0),
        "1.0-BETA",
        "1.03" /* xml output version I copied from their site */
        );
    fprintf(fp, "<scaninfo type=\"%s\" protocol=\"%s\" />\r\n",
        "syn", "tcp" );
}