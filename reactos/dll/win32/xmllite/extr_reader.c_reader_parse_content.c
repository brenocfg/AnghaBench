#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int resumestate; } ;
typedef  TYPE_1__ xmlreader ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  XmlReadResumeState_CDATA 132 
#define  XmlReadResumeState_CharData 131 
#define  XmlReadResumeState_Comment 130 
 int XmlReadResumeState_Initial ; 
#define  XmlReadResumeState_PIBody 129 
#define  XmlReadResumeState_PITarget 128 
 char const* commentW ; 
 char const* ltW ; 
 char const* piW ; 
 int /*<<< orphan*/  reader_cmp (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  reader_parse_cdata (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_chardata (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_comment (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_element (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_endtag (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_pi (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 

__attribute__((used)) static HRESULT reader_parse_content(xmlreader *reader)
{
    static const WCHAR cdstartW[] = {'<','!','[','C','D','A','T','A','[',0};
    static const WCHAR etagW[] = {'<','/',0};

    if (reader->resumestate != XmlReadResumeState_Initial)
    {
        switch (reader->resumestate)
        {
        case XmlReadResumeState_CDATA:
            return reader_parse_cdata(reader);
        case XmlReadResumeState_Comment:
            return reader_parse_comment(reader);
        case XmlReadResumeState_PIBody:
        case XmlReadResumeState_PITarget:
            return reader_parse_pi(reader);
        case XmlReadResumeState_CharData:
            return reader_parse_chardata(reader);
        default:
            ERR("unknown resume state %d\n", reader->resumestate);
        }
    }

    reader_shrink(reader);

    /* handle end tag here, it indicates end of content as well */
    if (!reader_cmp(reader, etagW))
        return reader_parse_endtag(reader);

    if (!reader_cmp(reader, commentW))
        return reader_parse_comment(reader);

    if (!reader_cmp(reader, piW))
        return reader_parse_pi(reader);

    if (!reader_cmp(reader, cdstartW))
        return reader_parse_cdata(reader);

    if (!reader_cmp(reader, ltW))
        return reader_parse_element(reader);

    /* what's left must be CharData */
    return reader_parse_chardata(reader);
}