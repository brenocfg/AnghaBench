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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ contains_char (char const*,size_t,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  isprint (char) ; 

__attribute__((used)) static void
nmapserviceprobes_print_hello(FILE *fp, const char *string, size_t length, int delimiter)
{
    size_t i;
    
    /* If the string contains the preferred delimiter, then choose a different
     * delimiter */
    if (contains_char(string, length, delimiter)) {
        static const char *delimiters = "|/\"'#*+-!@$%^&()_=";
        
        for (i=0; delimiters[i]; i++) {
            delimiter = delimiters[i];
            if (!contains_char(string, length, delimiter))
                break;
        }
    }
    
    /* print start delimiter */
    fprintf(fp, "%c", delimiter);
    
    /* print the string */
    for (i=0; i<length; i++) {
        char c = string[i];
        
        switch (c) {
            case '\\':
                fprintf(fp, "\\\\");
                break;
            case '\0':
                fprintf(fp, "\\0");
                break;
            case '\a':
                fprintf(fp, "\\a");
                break;
            case '\b':
                fprintf(fp, "\\b");
                break;
            case '\f':
                fprintf(fp, "\\f");
                break;
            case '\n':
                fprintf(fp, "\\n");
                break;
            case '\r':
                fprintf(fp, "\\r");
                break;
            case '\t':
                fprintf(fp, "\\t");
                break;
            case '\v':
                fprintf(fp, "\\v");
                break;
            default:
                if (isprint(c))
                    fprintf(fp, "%c", c);
                else
                    fprintf(fp, "\\x%02x", ((unsigned)c)&0xFF);
                break;
                
        }
    }
    
    /* print end delimiter */
    fprintf(fp, "%c", delimiter);
    
}