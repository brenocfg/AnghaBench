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
struct PcapFile {unsigned int byte_order; int /*<<< orphan*/  linktype; int /*<<< orphan*/ * fp; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  newname ;
typedef  int /*<<< orphan*/  linkspec ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int CAPFILE_BIGENDIAN ; 
 unsigned int CAPFILE_LITTLEENDIAN ; 
 scalar_t__ ENOENT ; 
 unsigned int PCAP16 (unsigned int,unsigned char*) ; 
 unsigned int PCAP32 (unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct PcapFile*,int /*<<< orphan*/ ,int) ; 
 struct PcapFile* pcapfile_openwrite (char const*,unsigned int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 size_t snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char const* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 

struct PcapFile *pcapfile_openappend(const char *capfilename, unsigned linktype)
{
    struct PcapFile *capfile;
    unsigned char buf[24];
    unsigned byte_order;
    unsigned file_linktype;
    FILE *fp;



    /* open the file for appending and reading */
    fp = fopen(capfilename, "ab+");
    if (fp == NULL && errno == ENOENT) {
        return pcapfile_openwrite(capfilename, linktype);
    }
    if (fp == NULL) {
        fprintf(stderr, "Could not open capture file to append frame\n");
        perror(capfilename);
        return pcapfile_openappend(capfilename, linktype);
    }

    /* Read in the header to discover link type and byte order */
    if (fread(buf, 1, 24, fp) != 24) {
        fprintf(stderr, "Error reading capture file header\n");
        perror(capfilename);
        fclose(fp);
        return pcapfile_openappend(capfilename, linktype);
    }

    /* Seek to the end of the file, where we will start writing
     * frames from now on. Note that we aren't checking to see if the frames
     * are corrupt at the end (which happens when the program crashes),
     * so we may end up writing these frames in a way that cannot be read. */
    if (fseek(fp, 0, SEEK_END) != 0) {
        fprintf(stderr, "Could not seek to end of capture file\n");
        perror(capfilename);
        fclose(fp);
        return 0;
    }


    /* Find out the byte order */
    switch (buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3]) {
    case 0xa1b2c3d4:   byte_order = CAPFILE_BIGENDIAN; break;
    case 0xd4c3b2a1:   byte_order = CAPFILE_LITTLEENDIAN; break;
    default:
        fprintf(stderr, "%s: unknown byte-order in cap file\n", capfilename);
        fclose(fp);
        return pcapfile_openappend(capfilename, linktype);
    }


    /* Version */
    {
        unsigned major = PCAP16(byte_order, buf+4);
        unsigned minor = PCAP16(byte_order, buf+6);

        if (major != 2 || minor != 4)
            fprintf(stderr, "%s: unknown version %u.%u\n", capfilename, major, minor);
    }

    /* Protocol */
    file_linktype = PCAP32(byte_order, buf+20);
    if (linktype != file_linktype) {
        /* oops, the link types do not agree. Since we want a program to generate
         * dumps while simultaneously processing multiple inputs, we are going to
         * create a kludge. Instead of writing to the originally specified file,
         * we are going to create a new file with the linktype added to it's name */
        char linkspec[32];
        size_t linkspec_length;
        char newname[sizeof(capfile->filename)];
        size_t i;

        fclose(fp);

        linkspec_length = snprintf(linkspec, sizeof(linkspec), "-linktype%d", linktype);

        if (strstr(capfilename, linkspec) || strlen(capfilename) + linkspec_length + 1 > sizeof(newname)) {
            /* Oops, we have a problem, it looks like the filename already
             * has the previous linktype in its name for some reason. At this
             * unlikely point, we just give up */
            fprintf(stderr, "Giving up on appending %u-type frames onto a %u-type file\n",
                    linktype, file_linktype);
            return 0;
        }

        if (strchr(capfilename, '.'))
            i = strchr(capfilename, '.')-capfilename;
        else
            i = strlen(capfilename);

        memcpy(newname, capfilename, i);
        memcpy(newname+i, linkspec, linkspec_length);
        memcpy(newname+i+linkspec_length, capfilename+i, strlen(capfilename+i)+1);

        return pcapfile_openappend(newname, linktype);
    }

    /* Now that everything has checked out, create a file structure and
     * return it */
    {

        capfile = (struct PcapFile*)malloc(sizeof(*capfile));
        if (capfile == NULL)
            exit(1);
        memset(capfile,0,sizeof(*capfile));
        capfile->byte_order = byte_order;
        snprintf(capfile->filename, sizeof(capfile->filename),
                 "%s", capfilename);
        capfile->fp = fp;
        capfile->byte_order = byte_order;
        capfile->linktype = linktype;
    }

    return capfile;
}