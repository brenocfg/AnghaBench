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

/* Variables and functions */
 int /*<<< orphan*/  LWAN_TPL_FLAG_CONST_TEMPLATE ; 
 int /*<<< orphan*/  index_desc ; 
 int /*<<< orphan*/  index_tpl ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 
 int /*<<< orphan*/  lwan_tpl_compile_string_full (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) __attribute__((constructor)) static void initialize_template(void)
{
    static const char index[] =
        "<html>\n"
        "<head>\n"
        "<style>\n"
        "body {\n"
        "   background:black;\n"
        "   height:100\x25;\n"
        "   text-align:center;\n"
        "   border:0;\n"
        "   margin:0;\n"
        "   padding:0;\n"
        "   font-family: sans-serif;\n"
        "}\n"
        "img {\n"
        "   image-rendering: pixelated;\n"
        "   image-rendering: -moz-crisp-edges;\n"
        "   image-rendering: crisp-edges;\n"
        "}\n"
        "#styles {\n"
        "   color: #444;\n"
        "   top: 0;\n"
        "   position: absolute;\n"
        "   padding: 16px;\n"
        "   left: calc(50% - 100px - 16px);\n"
        "   width: 250px;\n"
        "}\n"
        "#styles a, #styles a:visited, #lwan a, #lwan a:visited { color: #666; }\n"
        "#lwan {\n"
        "   color: #555;\n"
        "   top: calc(100% - 40px);\n"
        "   position: absolute;\n"
        "   height: 20px;\n"
        "   font-size: 75%;\n"
        "   width: 300px;\n"
        "}\n"
        "</style>\n"
        "<meta http-equiv=\"Refresh\" content=\"3600;url=/{{variant}}\">\n"
        "<title>{{title}}</title>\n"
        "</head>\n"
        "<body>\n"
        "  <div id=\"lwan\">\n"
        "    Powered by the <a href=\"https://lwan.ws\">Lwan</a> web server.\n"
        "  </div>\n"
        "  <table height=\"100\x25\" width=\"100\x25\">\n"
        "  <tr>\n"
        "    <td align=\"center\" valign=\"middle\">\n"
        "    <div><img src=\"/{{variant}}.gif\" width=\"{{width}}px\"></div>\n"
        "    </td>\n"
        "  </tr>\n"
        "  </table>\n"
        "  <div id=\"styles\">\n"
        "    Styles: "
        "<a href=\"/clock\">Digital</a> &middot; "
        "<a href=\"/dali\">Dali</a> &middot; "
        "<a href=\"/blocks\">Blocks</a>\n"
        "  </div>\n"
        "</body>\n"
        "</html>";

    index_tpl = lwan_tpl_compile_string_full(index, index_desc,
                                             LWAN_TPL_FLAG_CONST_TEMPLATE);
    if (!index_tpl)
        lwan_status_critical("Could not compile template");
}