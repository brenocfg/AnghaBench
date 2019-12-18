#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/  verbs; } ;
struct TYPE_5__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  Argument; int /*<<< orphan*/  Command; int /*<<< orphan*/  Sequence; int /*<<< orphan*/  Verb; } ;
typedef  TYPE_1__ MSIVERB ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_2__ MSIEXTENSION ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deformat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* load_given_extension (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_dup_record_field (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static UINT iterate_load_verb(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE* package = param;
    MSIVERB *verb;
    LPCWSTR buffer;
    MSIEXTENSION *extension;

    buffer = MSI_RecordGetString(row,1);
    extension = load_given_extension( package, buffer );
    if (!extension)
    {
        ERR("Verb unable to find loaded extension %s\n", debugstr_w(buffer));
        return ERROR_SUCCESS;
    }

    /* fill in the data */

    verb = msi_alloc_zero( sizeof(MSIVERB) );
    if (!verb)
        return ERROR_OUTOFMEMORY;

    verb->Verb = msi_dup_record_field(row,2);
    TRACE("loading verb %s\n",debugstr_w(verb->Verb));
    verb->Sequence = MSI_RecordGetInteger(row,3);

    buffer = MSI_RecordGetString(row,4);
    deformat_string(package,buffer,&verb->Command);

    buffer = MSI_RecordGetString(row,5);
    deformat_string(package,buffer,&verb->Argument);

    /* associate the verb with the correct extension */
    list_add_tail( &extension->verbs, &verb->entry );
    
    return ERROR_SUCCESS;
}