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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 char* GetMultiByteString (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closeKey () ; 
 scalar_t__ currentKeyHandle ; 
 int /*<<< orphan*/  delete_registry_key (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getAppName () ; 
 scalar_t__ openKeyW (char*) ; 
 int /*<<< orphan*/  processSetValue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchrW (char*,char) ; 

__attribute__((used)) static void processRegEntry(WCHAR* stdInput, BOOL isUnicode)
{
    /*
     * We encountered the end of the file, make sure we
     * close the opened key and exit
     */
    if (stdInput == NULL) {
        closeKey();
        return;
    }

    if      ( stdInput[0] == '[')      /* We are reading a new key */
    {
        WCHAR* keyEnd;
        closeKey();                    /* Close the previous key */

        /* Get rid of the square brackets */
        stdInput++;
        keyEnd = strrchrW(stdInput, ']');
        if (keyEnd)
            *keyEnd='\0';

        /* delete the key if we encounter '-' at the start of reg key */
        if ( stdInput[0] == '-')
        {
            delete_registry_key(stdInput + 1);
        } else if ( openKeyW(stdInput) != ERROR_SUCCESS )
        {
            char* stdInputA = GetMultiByteString(stdInput);
            fprintf(stderr,"%S: setValue failed to open key %s\n",
                    getAppName(), stdInputA);
            HeapFree(GetProcessHeap(), 0, stdInputA);
        }
    } else if( currentKeyHandle &&
               (( stdInput[0] == '@') || /* reading a default @=data pair */
                ( stdInput[0] == '\"'))) /* reading a new value=data pair */
    {
        processSetValue(stdInput, isUnicode);
    } else
    {
        /* Since we are assuming that the file format is valid we must be
         * reading a blank line which indicates the end of this key processing
         */
        closeKey();
    }
}