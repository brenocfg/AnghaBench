#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ resumestate; scalar_t__* resume; int /*<<< orphan*/  nodetype; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_Value ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_E_COMMENT ; 
 int /*<<< orphan*/  XmlNodeType_Comment ; 
 scalar_t__ XmlReadResumeState_Comment ; 
 scalar_t__ XmlReadResumeState_Initial ; 
 size_t XmlReadResume_Body ; 
 int /*<<< orphan*/  debug_strval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ reader_get_cur (TYPE_1__*) ; 
 char* reader_get_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 

__attribute__((used)) static HRESULT reader_parse_comment(xmlreader *reader)
{
    WCHAR *ptr;
    UINT start;

    if (reader->resumestate == XmlReadResumeState_Comment)
    {
        start = reader->resume[XmlReadResume_Body];
        ptr = reader_get_ptr(reader);
    }
    else
    {
        /* skip '<!--' */
        reader_skipn(reader, 4);
        reader_shrink(reader);
        ptr = reader_get_ptr(reader);
        start = reader_get_cur(reader);
        reader->nodetype = XmlNodeType_Comment;
        reader->resume[XmlReadResume_Body] = start;
        reader->resumestate = XmlReadResumeState_Comment;
        reader_set_strvalue(reader, StringValue_Value, NULL);
    }

    /* will exit when there's no more data, it won't attempt to
       read more from stream */
    while (*ptr)
    {
        if (ptr[0] == '-')
        {
            if (ptr[1] == '-')
            {
                if (ptr[2] == '>')
                {
                    strval value;

                    reader_init_strvalue(start, reader_get_cur(reader)-start, &value);
                    TRACE("%s\n", debug_strval(reader, &value));

                    /* skip rest of markup '->' */
                    reader_skipn(reader, 3);

                    reader_set_strvalue(reader, StringValue_Value, &value);
                    reader->resume[XmlReadResume_Body] = 0;
                    reader->resumestate = XmlReadResumeState_Initial;
                    return S_OK;
                }
                else
                    return WC_E_COMMENT;
            }
        }

        reader_skipn(reader, 1);
        ptr++;
    }

    return S_OK;
}