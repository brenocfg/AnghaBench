#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int format; } ;
struct TYPE_3__ {int ip; int port; } ;
struct Masscan {TYPE_2__ output; TYPE_1__ redis; int /*<<< orphan*/  echo_all; int /*<<< orphan*/ * echo; } ;
typedef  enum OutputFormat { ____Placeholder_OutputFormat } OutputFormat ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CONF_ERR ; 
 int CONF_OK ; 
 scalar_t__ EQUALS (char*,char const*) ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,...) ; 
#define  Output_Binary 139 
#define  Output_Certs 138 
#define  Output_Default 137 
#define  Output_Grepable 136 
#define  Output_Interactive 135 
#define  Output_JSON 134 
#define  Output_List 133 
#define  Output_NDJSON 132 
#define  Output_None 131 
#define  Output_Redis 130 
#define  Output_Unicornscan 129 
#define  Output_XML 128 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int SET_output_format(struct Masscan *masscan, const char *name, const char *value)
{
    enum OutputFormat x = 0;
    UNUSEDPARM(name);
    if (masscan->echo) {
        FILE *fp = masscan->echo;
        switch (masscan->output.format) {
            case Output_Default:    if (masscan->echo_all) fprintf(fp, "output-format = interactive\n"); break;
            case Output_Interactive:fprintf(fp, "output-format = interactive\n"); break;
            case Output_List:       fprintf(fp, "output-format = list\n"); break;
            case Output_Unicornscan:fprintf(fp, "output-format = unicornscan\n"); break;
            case Output_XML:        fprintf(fp, "output-format = xml\n"); break;
            case Output_Binary:     fprintf(fp, "output-format = binary\n"); break;
            case Output_Grepable:   fprintf(fp, "output-format = grepable\n"); break;
            case Output_JSON:       fprintf(fp, "output-format = json\n"); break;
            case Output_NDJSON:     fprintf(fp, "output-format = ndjson\n"); break;
            case Output_Certs:      fprintf(fp, "output-format = certs\n"); break;
            case Output_None:       fprintf(fp, "output-format = none\n"); break;
            case Output_Redis:
                fprintf(fp, "output-format = redis\n");
                fprintf(fp, "redis = %u.%u.%u.%u:%u\n",
                        (unsigned char)(masscan->redis.ip>>24),
                        (unsigned char)(masscan->redis.ip>>16),
                        (unsigned char)(masscan->redis.ip>> 8),
                        (unsigned char)(masscan->redis.ip>> 0),
                        masscan->redis.port);
                break;
                
            default:
                fprintf(fp, "output-format = unknown(%u)\n", masscan->output.format);
                break;
        }
        return 0;
    }
    if (EQUALS("unknown(0)", value))        x = Output_Interactive;
    else if (EQUALS("interactive", value))  x = Output_Interactive;
    else if (EQUALS("list", value))         x = Output_List;
    else if (EQUALS("unicornscan", value))  x = Output_Unicornscan;
    else if (EQUALS("xml", value))          x = Output_XML;
    else if (EQUALS("binary", value))       x = Output_Binary;
    else if (EQUALS("greppable", value))    x = Output_Grepable;
    else if (EQUALS("grepable", value))     x = Output_Grepable;
    else if (EQUALS("json", value))         x = Output_JSON;
    else if (EQUALS("ndjson", value))       x = Output_NDJSON;
    else if (EQUALS("certs", value))        x = Output_Certs;
    else if (EQUALS("none", value))         x = Output_None;
    else if (EQUALS("redis", value))        x = Output_Redis;
    else {
        LOG(0, "FAIL: unknown output-format: %s\n", value);
        LOG(0, "  hint: 'binary', 'xml', 'grepable', ...\n");
        return CONF_ERR;
    }
    masscan->output.format = x;

    return CONF_OK;
}