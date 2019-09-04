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
struct SMACK {int dummy; } ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  smack_add_pattern (struct SMACK*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_compile (struct SMACK*) ; 
 struct SMACK* smack_create (char*,int) ; 
 int /*<<< orphan*/  smack_destroy (struct SMACK*) ; 
 size_t smack_search_next (struct SMACK*,unsigned int*,char const*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 

int
smack_selftest(void)
{
    struct SMACK *s;

    
        const char *patterns[] = {
            "GET",      "PUT",      "POST",     "OPTIONS",
            "HEAD",     "DELETE",   "TRACE",    "CONNECT",
            "PROPFIND", "PROPPATCH","MKCOL",    "MKWORKSPACE",
            "MOVE",     "LOCK",     "UNLOCK",   "VERSION-CONTROL",
            "REPORT",   "CHECKOUT", "CHECKIN",  "UNCHECKOUT",
            "COPY",     "UPDATE",   "LABEL",    "BASELINE-CONTROL",
            "MERGE",    "SEARCH",   "ACL",      "ORDERPATCH",
            "PATCH",    "MKACTIVITY", 0};
        unsigned i;
        const char *text = "ahpropfinddf;orderpatchposearchmoversion-controlockasldhf";
        unsigned text_length = (unsigned)strlen(text);
        size_t id;
        unsigned state = 0;

        /*
         * using SMACK is 5 steps:
         * #1 create an instance at program startup
         * #2 add patterns to it
         * #3 compile the patterns
         * #4 do your searches while running the program
         * #5 destroy the instance at program exit
         */
        s = smack_create("test1", 1);

        for (i=0; patterns[i]; i++)
            smack_add_pattern(s, patterns[i], (unsigned)strlen(patterns[i]), i, 0);

        smack_compile(s);

        i = 0;
#define TEST(pat, offset, str) if (pat != id || offset != i) return 1 + fprintf(stderr, "smack: fail %s\n", str)
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST(  8,  10, "PROPFIND");
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST( 28,  23, "PATCH");
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST( 27,  23, "ORDERPATCH");
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST( 25,  31, "SEARCH");
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST( 12,  35, "MOVE");
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST( 15,  48, "VERSION-CONTROL");
        id = smack_search_next(s,&state,text, &i,text_length);
        TEST( 13,  51, "LOCK");

        /*{
            unsigned i;
            for (i=0; i<s->m_state_count; i++) {
                if (s->m_match[i].m_count)
                    printf("*");
                else
                    printf(".");
            }
            printf("\n");
        }*/
        smack_destroy(s);

    


    return 0;
}