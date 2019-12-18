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
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  Addhost (char*,char*,char*) ; 
 int /*<<< orphan*/  Deletehost (char*,char*) ; 
 int /*<<< orphan*/  DisplayArpEntries (char*,char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

INT main(int argc, char* argv[])
{
    if ((argc < 2) || (argc > 5))
    {
       Usage();
       return EXIT_FAILURE;
    }

    if (argv[1][0] == '-')
    {
        switch (argv[1][1])
        {
           case 'a': /* fall through */
           case 'g':
                     if (argc == 2)
                         DisplayArpEntries(NULL, NULL);
                     else if (argc == 3)
                         DisplayArpEntries(argv[2], NULL);
                     else if ((argc == 4) && ((strcmp(argv[2], "-N")) == 0))
                         DisplayArpEntries(NULL, argv[3]);
                     else if ((argc == 5) && ((strcmp(argv[3], "-N")) == 0))
                         DisplayArpEntries(argv[2], argv[4]);
                     else
                     {
                         Usage();
                         return EXIT_FAILURE;
                     }
                     break;
           case 'd': if (argc == 3)
                         Deletehost(argv[2], NULL);
                     else if (argc == 4)
                         Deletehost(argv[2], argv[3]);
                     else
                     {
                         Usage();
                         return EXIT_FAILURE;
                     }
                     break;
           case 's': if (argc == 4)
                         Addhost(argv[2], argv[3], NULL);
                     else if (argc == 5)
                         Addhost(argv[2], argv[3], argv[4]);
                     else
                     {
                         Usage();
                         return EXIT_FAILURE;
                     }
                     break;
           default:
              Usage();
              return EXIT_FAILURE;
        }
    }
    else
        Usage();

    return EXIT_SUCCESS;
}